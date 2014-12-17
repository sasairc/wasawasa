/*
 * やすなちゃんかわいい
 */
 
#define MODNAME "wasawasa"
#define CD_MAJOR        254
#define CD_MINORS       1

#include <linux/semaphore.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

MODULE_LICENSE("WTFPL");
MODULE_AUTHOR("sasairc");

static struct cdev cdev;
static struct semaphore cdev_sem;

static int chardev_open(struct inode *inode, struct file *file)
{
        return 0;
}

static int chardev_release(struct inode *inode, struct file *file)
{
        return 0;
}

static ssize_t chardev_read(struct file *file, char *buf, size_t count, loff_t *offset)
{
        char *str = "wasawasa";

        down_interruptible(&cdev_sem);
        copy_to_user(buf, str, (sizeof(str) + 1));

        *offset += (sizeof(str) + 1);
        up(&cdev_sem);
        return (sizeof(str) + 1);
}

static struct file_operations cdev_fops = {
        .owner  = THIS_MODULE,
        .open   = chardev_open,
        .read   = chardev_read,
        .release = chardev_release,
};

static int __init chardev_init(void)
{
        int ret;
        dev_t dev;

        dev = MKDEV(CD_MAJOR, 0);
        cdev_init(&cdev, &cdev_fops);

        ret = cdev_add(&cdev, dev, CD_MINORS);
        if (ret < 0) {
                printk(KERN_WARNING "%s: cdev_add() failure.\n", MODNAME);
                return ret;
        }

        sema_init(&cdev_sem, 1);

        return 0;
}

static void __exit chardev_exit(void)
{
        dev_t dev;

        dev = MKDEV(CD_MAJOR, 0);
        cdev_del(&cdev);
        unregister_chrdev_region(dev, CD_MINORS);
}

module_init(chardev_init);
module_exit(chardev_exit);
