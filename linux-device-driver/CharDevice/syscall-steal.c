/**
 * syscall-steal.c
 *
 * System call "stealing" sample
 *
 * Disables page protection at a processor level by changing the 16th bit
 * in the cr0 register (could be Intel specific)
 */
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>  /* which will have params */
#include <linux/unistd.h>       /* The list of system calls */
#include <linux/cred.h>         /* For current_uid() */
#include <linux/uidgid.h>       /* For __kuid_val() */
#include <linux/version.h>

/**
 * For the current (process) structure, we need this to know who the current user is
 */
#include <linux/sched.h>
#include <linux/uaccess.h>

/**
 * The in kernel calls to the ksys_close() syscall were removed in linux v5.11+
 */
#if (LINUX_VERSION_CODE < KERNEL_VERSION(5, 7, 0))
#if LINUX_VERSION_CODE <= KERNEL_VERSION(5, 4, 0)
#define HAVE_KSYS_CLOSE 1
#include <linux/syscalls.h>   /* For ksys_close() */
#else
#include <linux/kallsyms.h>   /* For kallsyms_lookup_name */
#endif

#else

#if defined(CONFIG_KPROBES)
#define HAVE_KPROBES 1
#if defined(CONFIG_X86_64)
/**
 * If you have tried to use the syscall table to intercept syscalls and it 
 * does not work, you can try to use Kprobes to intercept syscalls
 * Set USE_KPROBES_PRE_HANDLER_BEFORE_SYSCALL to 1 to register a pre-handler before
 * the syscall.
 */
#define USE_KPROBES_PRE_HANDLER_BEFORE_SYSCALL 0
#endif
#include <linux/kprobes.h>
#else
#define HAVE_PARAM 1
#include <linux/kallsyms.h> /* For sprint_symbol */
/**
 * The address of the sys_call_table, which can be obtained with looking up 
 * "/boot/System.map" of "/proc/kallsyms". When the kernel version is v5.7+ without
 * CONFIG_KPROBES, you can input the parameter or the module will look up all the memory
 */
static unsigned long sym = 0;
module_param(sym, ulong, 0644);
#endif /* CONFIG_KPROBES */
#endif /* Version < v5.7 */

/* UID we want to spy on will be filled from the command line */
static uid_t uid = -1;
module_param(uid, int, 0644);

#if USE_KPROBES_PRE_HANDLER_BEFORE_SYSCALL

/**
 * syscall_sm is the symbol name of the syscall to spy on. The default is 
 * "__x64_sys_openat", which can be changed by the module parameter. You can look up
 * the symbol name of a syscall in /proc/kallsyms.
 */
static char *syscall_sym = "__x64_sys_openat";
module_param(syscall_sm, charp, 0644);

static int sys_call_kprobe_pre_handler(struct kprobe *p, struct pt_regs *regs)
{
  if (__kuid_val(current_uid()) != uid) {
    return 0;
  }
  pr_info("%s called by %d\n", syscall_sm, uid);
  return 0;
}

static struct kprobe syscall_kprobe = {
  .symbol_name = "__x64_sys_openat",
  .pre_handler = sys_call_kprobe_pre_handler,
};

static unsigned long **sys_call_table_stolen;

/**
 * A pointer to the original system call. The reason we keep this, rather than call
 * the original function (sys_openat), is because somebody else might have replaced 
 * the system call before us. Note that this is not 100% safe, because if another
 * module replaced sys_openat before us, then when we are inserted, we will call the 
 * function in that module and it might be removed before we are.
 *
 * Another reason for this is that we can not get sys_openat 
 * it is a static variable, so it is not exported
 */
#ifdef CONFIG_ARCH_HAS_SYSCALL_WRAPPER
static asmlinkage long (*original_call)(const struct pt_regs *);
#else
static asmlinkage long (*original_call)(int, const char __user *, int, umode_t);
#endif

/**
 * This function we wil
