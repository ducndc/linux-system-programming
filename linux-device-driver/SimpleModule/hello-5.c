/**
 * hello-5.c - The simplest kernel module.
 */
#include <linux/init.h>   /* Needed for the macros */
#include <linux/kernel.h> /* for ARRAY_SIZE() */
#include <linux/module.h> /* Needed by all modules */
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/stat.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DUCNDC");
MODULE_DESCRIPTION("A sample driver");

static short int myshort = 1;
static int myint = 420;
static long int mylong = 9999;
static char *mystring = "string";
static int myintarray[2] = {420, 420};
static int arr_argc = 0;

/**
 * module_param(foo, int, 0000)
 * The first param is the paramater's name.
 * The second param is its data type.
 * The final argument is the permissions bits,
 * for exposing paramaters in sysfs (if non-zero) at a later stage.
 */
module_param(myshort, short, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
MODULE_PARM_DESC(myshort, "A short interger");
module_param(myint, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(myint, "An interger");
module_param(mylong, long, S_IRUSR);
MODULE_PARM_DESC(mylong, "A long interger");
module_param(mystring, charp, 0000);
MODULE_PARM_DESC(mystring, "A character string");

/* module_param_array(name, type, num, perm);
 * The first param is the parameter's (in this case the array's) name.
 * The second param is the data type of the elements of the array.
 * The third argument is a pointer to the variable that will store the number
 * of elements of the array initialized by the user at module loading time.
 * The fourth argument is the permission bits.
 */
module_param_array(myintarray, int, &arr_argc, 0000);
MODULE_PARM_DESC(myintarray, "An array of integers");

static int __init hello_5_init(void)
{
    int i;

    pr_info("Hello, world 5\n=============\n");
    pr_info("myshort is a short integer: %hd\n", myshort);
    pr_info("myint is an integer: %d\n", myint);
    pr_info("mylong is a long integer: %ld\n", mylong);
    pr_info("mystring is a string: %s\n", mystring);

    for (i = 0; i < ARRAY_SIZE(myintarray); i++)
        pr_info("myintarray[%d] = %d\n", i, myintarray[i]);

    pr_info("got %d arguments for myintarray.\n", arr_argc);
    return 0;
}

static void __exit hello_5_exit(void)
{
    pr_info("Goodbye, world 5\n");
}

module_init(hello_5_init);
module_exit(hello_5_exit);
