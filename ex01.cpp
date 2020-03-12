#include <stdio.h>
#include <stdlib.h>
// #include <cstring>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <libv4l2.h>


int main()
{
	int fd = v4l2_open("/dev/video0", O_RDWR | O_NONBLOCK, 0);
	struct v4l2_input input;
	int index;
	if (-1 == ioctl (fd, VIDIOC_G_INPUT, &index)) {
		perror("VIDIOC_G_INPUT");
		exit (EXIT_FAILURE);
	}
	memset (&input, 0, sizeof (input));
	input.index = index;
	if (-1 == ioctl (fd, VIDIOC_ENUMINPUT, &input)) {
		perror ("VIDIOC_ENUMINPUT");
		exit (EXIT_FAILURE);
	}
	printf ("Current input: %s\n", input.name);
}
