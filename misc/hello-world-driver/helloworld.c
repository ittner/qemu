

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/major.h>
#include <linux/string.h>
#include <linux/fcntl.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <asm/uaccess.h>


/* http://linux.die.net/lkmpg/x569.html */

#define DEV_MAJOR 242
#define DEV_NAME "helloworld"

const static char *dummy_data = "Hello, world!";



static int mod_open(struct inode *inode, struct file *file)
{
	try_module_get(THIS_MODULE);
	return 0;
}

static int mod_release(struct inode *inode, struct file *file)
{
	module_put(THIS_MODULE);
	return 0;
}

ssize_t mod_read(struct file *filep, char *buf, size_t nbytes, loff_t *offp)
{
	size_t len = strlen(dummy_data);
	if (copy_to_user(buf, dummy_data, len) != 0) {
		printk("Kernel -> userspace copy failed!\n");
		return -1;
	}
	return len;
}

ssize_t mod_write(struct file *filep, const char *buf, size_t nbytes, loff_t *offp)
{
	return 0;
}

static struct file_operations mod_ops = {
	.open = mod_open,
	.release = mod_release,
	.read = mod_read,
	.write = mod_write
};





static int mod_init(void)
{
	int ret = register_chrdev(DEV_MAJOR, DEV_NAME, &mod_ops);
	printk(DEV_NAME " mod_init: register_chrdev --> %d\n", ret);
	return 0;
}

static void mod_exit(void)
{
	printk(DEV_NAME " mod_exit: unregister_chrdev\n");
	unregister_chrdev(DEV_MAJOR, DEV_NAME);

}

module_init(mod_init);
module_exit(mod_exit);

MODULE_AUTHOR("Alexandre Erwin Ittner");
MODULE_DESCRIPTION("Hello World device");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");
