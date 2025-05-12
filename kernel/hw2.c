#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/errno.h>
#include <linux/list.h>

asmlinkage long sys_hello(void) {
    printk("Hello, World!\n");
    return 0;
}

asmlinkage long sys_set_weight(int weight) {
    if(weight < 0) {
        return -EINVAL;
    }
    else {
        current->weight = weight;
        return 0;
    }
}

asmlinkage long sys_get_weight(void) {
    printk("Inside get_weight");
    return current->weight;
}

asmlinkage long sys_get_siblings_sum(void) {
    int sum = 0;
    struct list_head* list;
    struct list_entry* entry;
    if(list_is_singular(current->sibling) {
        return -ESRCH;
    }
    list_for_each(list, &current->sibling) {
        struct task_struct* curr_sibling = list_entry(list, struct task_struct, sibling);
        if (curr_sibling != current) {
            sum += curr_sibling->weight;
        }
    }
    return sum;
}

asmlinkage long sys_get_lightest_divisor_ancestor(void) {
    struct task_struct* curr_ancestor = current->real_parent;
    struct task_struct* min_weight_ancestor = current;
	if (current->weight == 0) {
		return current->pid;
	}
    while(curr_ancestor->pid != 0) {
            if((curr_ancestor->weight < min_weight_ancestor->weight) && (current->weight % curr_ancestor->weight == 0) && (curr_ancestor->weight != 0)) {
                min_weight_ancestor = curr_ancestor;
            }
        curr_ancestor = curr_ancestor->real_parent;
    }
    return min_weight_ancestor->pid;
}

