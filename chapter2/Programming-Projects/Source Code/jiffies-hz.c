#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/jiffies.h>
#include <asm/param.h>
/* This function is called when the module is loaded. */
static int simple_init(void)
{
printk(KERN_INFO "Loading Module\n");
printk(KERN_INFO "HZ Value: %lu\n", HZ);
printk(KERN_INFO "Jiffies Value: %lu\n",jiffies);
return 0;
}
/* This function is called when the module is removed. */
static void simple_exit(void) {
printk(KERN_INFO "Removing Module\n");
printk(KERN_INFO "Jiffies Value: %lu\n", jiffies);
}
/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("Ahmed Moustafa");
