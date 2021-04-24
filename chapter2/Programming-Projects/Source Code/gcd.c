#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/hash.h>
#include <linux/gcd.h>
/* This function is called when the module is loaded. */
static int simple_init(void)
{
printk(KERN_INFO "Loading Module\n");
printk(KERN_INFO "The Golden Prime Ratio: %lu\n", GOLDEN_RATIO_PRIME);
return 0;
}
/* This function is called when the module is removed. */
static void simple_exit(void) {
printk(KERN_INFO "Removing Module\n");
printk(KERN_INFO "The GCD of 3300 and 24 is: %lu\n", gcd(3300, 24));
}
/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("Ahmed Moustafa");
