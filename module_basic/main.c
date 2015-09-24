#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>


#define AUTHOR        "Author Name <author.name@mail.com>"
#define DESCRIPTION   "This is a test module"
#define LICENSE       "Dual BSD/GPL"


static int m_int = 123; // with default value
static char* m_string = "test";

module_param(m_int, int, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
MODULE_PARM_DESC(m_int, "An integer");

module_param(m_string, charp, 0000);
MODULE_PARM_DESC(m_string, "A character string");


int __init my_module_init(void) {

  printk(KERN_ALERT "Hello, world\n");
  printk(KERN_ALERT "int: %d\n", m_int);
  printk(KERN_ALERT "str: %s\n", m_string);
  return 0;
}


void __exit my_module_exit(void) {

  printk(KERN_ALERT "Goodbye, world\n");
}


module_init(my_module_init);
module_exit(my_module_exit);


MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESCRIPTION); 
MODULE_LICENSE(LICENSE);
