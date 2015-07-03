#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#define SENSOR_ADDR 0x39

int i2c_open(int *fd, char *filename, int addr)
{
	//open I2C device file
	if((*fd=open(filename, O_RDWR))<0) 
	{
		fprintf(stderr, "i2c_open: Faild to open i2c port\n");
		return -1;
	}
	//set device address
	if(ioctl(*fd, I2C_SLAVE, addr)<0) 
	{
		fprintf(stderr, "i2c_open: Failed to talk to slave\n");
		return -2;
	}
	
	return 0;
}

int i2c_close(char fd)
{
	//close I2C device file
	if((close(fd))<0) 
	{
		fprintf(stderr, "i2c_close: Faild to close i2c port\n");
		return -1;
	}
	
	return 0;
}

int i2c_write(int fd, unsigned char regaddr, unsigned char data)
{
	unsigned char buf[2];
	buf[0]=regaddr;
	buf[1]=data;
	
	if((write(fd,buf,2))!=2){
		fprintf(stderr, "i2c_write: Error writing to i2c slave\n");
		return -1;
	}
	
	return 0;
}

int i2c_read(int fd, unsigned char regaddr)
{
	unsigned char buf[1];
	buf[0]=regaddr;
	
	if((write(fd,buf,1))!=1){ //note: write an address once
		fprintf(stderr, "i2c_read: Error writing to i2c slave\n");
		return -1;
	}
	if(read(fd,buf,1)!=1){
		fprintf(stderr, "i2c_read: Error reading from i2c slave\n");
		return -2;
	}
	
	return buf[0];
}

int main(int argc, char **argv)
{
	char *i2cFileName="/dev/i2c-0";  //Device address 
	int i2c_fd_sensor;               //I2C device file descriptor
	int i2c_addr_sensor=SENSOR_ADDR; //I2C device address
	int ret;
	unsigned char th, tl;
	double temperature;
	
	//Open I2C device: Temperature sensor STTS751
	ret=i2c_open(&i2c_fd_sensor, i2cFileName, i2c_addr_sensor);
	if(ret<0){
		fprintf(stderr, "main: Failed i2c_open\n");
		exit(EXIT_FAILURE);
	}
	
	//Write configuration to STTS751
	ret=i2c_write(i2c_fd_sensor, 0x03, 0x0C);
	if(ret<0){
		fprintf(stderr, "main: Failed i2c_write\n");
		exit(EXIT_FAILURE);
	}
	
	//Read address 00 from STTS751
	ret=i2c_read(i2c_fd_sensor, 0x00);
	if(ret<0){
		fprintf(stderr, "main: Failed i2c_read (address 00)\n");
		exit(EXIT_FAILURE);
	}
	th=(unsigned char)ret;
	//Read address 02 from STTS751
	ret=i2c_read(i2c_fd_sensor, 0x02);
	if(ret<0){
		fprintf(stderr, "main: Failed i2c_read (address 02)\n");
		exit(EXIT_FAILURE);
	}
	tl=(unsigned char)ret;
	
	//Close device: STTS751
	ret=i2c_close(i2c_fd_sensor);
	if(ret<0){
		fprintf(stderr, "main: Failed i2c_close\n");
		exit(EXIT_FAILURE);
	}
	
	//Calculate temperature
	temperature=(double)th+((double)(tl>>4)*0.0625);
	printf("%.1lf", temperature);
	
	return 0;
}
 
