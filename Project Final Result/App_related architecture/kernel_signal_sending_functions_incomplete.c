/* Incomplete */
/* Tried to implement the architecture which is described on the report */

static pid_t sender_pid = 0;
static int pending_alert = 0;

static int __init xx_init(void) {
	pf = create_proc_entry("sender_pid", 0644, NULL);
	if(pf == NULL) {
		printk(KERN_ERR "Could not create proc for fake ACK sender\n");
	} else {
		pf->read_proc = sender_read;
		pf->write_proc = sender_write;
	}

	return 0;
}

void send_signal_to_sender(void)
{
	int ret;
	struct task_struct *tsk;
	printk(KERN_INFO "send_signal_to_sender\n");
	if(sender_pid == 0) {
		pending_alert = 1;
	} else {
		printk(KERN_INFO "isender pid=%d\n", sender_pid);
		tsk = find_task_by_vpid(sender_pid);
		printk(KERN_INFO "tsk=%x\n", (int)tsk);
		if(tsk) {
			ret = send_sig_info(SIGUSR1, SEND_SIG_NOINFO, tsk);
			printk(KERN_INFO "ret=%d\n", ret);
		}
	}
}

static int sender_read(char *buffer, char **buffer_location, off_t offset, int buffer_length, int *eof, void *data)
{
	int len;
	len = snprintf(buffer, PAGE_SIZE, "%d\n", sender_pid);
	return proc_calc_metrics(buffer, buffer_location, offset, buffer_length, eof, len);
}

static int sender_write(struct file *file, const char *buffer, unsigned long count, void *data)
{
	int len;
	char buf[16];
	if(count>16)
		len = 16;
	else
		len = count;
	if(copy_from_user(buf, buffer, len))
		return -EFAULT;
	buf[len] = '\0';
	printk(KERN_INFO "sender_write: '%s'\n", buf);
	sscanf(buf, "%d", &sender_pid);
	printk(KERN_INFO "sender_write: pid = %d\n", sender_pid);
	if(pending_alert) {
		send_signal_to_sender();
		pending_alert = 0;
	}
	return len;
}

static int
proc_calc_metrics(char *page, char **start, off_t off, int count, int *eof,
		  int len)
{
	if (len <= off + count)
		*eof = 1;
	*start = page + off;
	len -= off;
	if (len > count)
		len = count;
	if (len < 0)
		len = 0;
	return len;
}

