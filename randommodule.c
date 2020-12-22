#include <linux/module.h> 	//Khai bao Linux kernel module
#include <linux/random.h> 	//Khai bao trinh tao so ngau nhien
#include <linux/init.h>   	//Khai bao init
#include <linux/kernel.h> 	//Khai bao kernel
#include <linux/types.h>	//major,minor number
#include <linux/device.h>  	//device init
#include <linux/fs.h>     	//file va he thong
#include <linux/uaccess.h>	//copy_to_user


static struct class *cl = NULL;		//class device
static struct device *dev = NULL;	//device
static int major;			//major number

static int dev_open(struct inode *i, struct file *f){
    printk(KERN_INFO "Driver: open()\n");
    return 0;
}

static int dev_close(struct inode *i, struct file *f)
{
    printk(KERN_INFO "Driver: close()\n");
    return 0;
}

static ssize_t dev_read(struct file *filep, char *usr_space, size_t len, loff_t *offset) {
    int randomValue;
    get_random_bytes(&randomValue, sizeof(randomValue));

    // return 0 if success
    if (!copy_to_user(usr_space, &randomValue, sizeof(randomValue))) {
        printk(KERN_INFO "Driver: succesfully generate random number\n");
        return 0;
    }
    else {
        printk(KERN_INFO "Driver: error generate random number\n");
        return -EFAULT;
    }
}

//Cau truc file operation, gan dia chi ham cho cac truong open, read va release
static struct file_operations fops =
        {
                .open = dev_open,
                .read = dev_read,
                .release = dev_close
        };


static int __init ofcd_init(void) {
    //khoi tao major number va kiem tra ngoai le
    major = register_chrdev(0, "randnumber", &fops);
    if (major < 0) {
        printk(KERN_ALERT "Driver: failed to reg major number\n");
        return major;
    }

    //khoi tao class dev  va kiem tra ngoai le
    cl = class_create(THIS_MODULE, "randomDriver");

    if (IS_ERR(cl)) {
        unregister_chrdev(major, "randnumber");
        printk(KERN_ALERT "Driver: failed to reg dev class\n");
        return PTR_ERR(cl);
    }

    //khoi tao dev va kiem tra ngoai le
    dev = device_create(cl, NULL, MKDEV(major, 0), NULL, "randnumber");
    if (IS_ERR(dev)) {
        unregister_chrdev(major, "randnumber");
        printk(KERN_ALERT "Driver: failed to register dev driver\n");
        return PTR_ERR(dev);
    }
    return 0;
}


static void __exit ofcd_exit(void) {
    //unregister truoc khi destroy
    device_destroy(cl, MKDEV(major, 0));
    class_unregister(cl);
    class_destroy(cl);
    unregister_chrdev(major, "randnumber");
    printk(KERN_INFO "ofcd unregistered");
}



module_init(ofcd_init); 
module_exit(ofcd_exit); 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nguyen Cao Dang Khoa - Nguyen Tien Tai - Le Tho Dat");