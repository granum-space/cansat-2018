#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>

#include <nuttx/wireless/nrf24l01.h>

#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int nrf_test_main(int argc, char *argv[])
#endif
{
  printf("This is NRF24L01+ test app!\n");
  int fd = open("/dev/nrf24l01", O_RDWR);
  if (fd < 0)
  {
      perror("Can't open /dev/nrf24l01");
      return 1;
  }

  volatile int ret;

  uint32_t tmp = 2476;
  ret = ioctl(fd, WLIOC_SETRADIOFREQ, &tmp);
  ret = ioctl(fd, WLIOC_GETRADIOFREQ, &tmp);
  printf("Frequency is %d MHz\n", tmp);

  tmp = 5;
  ret = ioctl(fd, NRF24L01IOC_SETADDRWIDTH, &tmp);

  uint8_t addr[] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};
  ret = ioctl(fd, NRF24L01IOC_SETTXADDR, addr);

  tmp = 0;
  ret = ioctl(fd, WLIOC_SETTXPOWER, &tmp);

  nrf24l01_retrcfg_t retrcfg = {.delay = DELAY_4000us, .count = 10};
  ret = ioctl(fd, NRF24L01IOC_SETRETRCFG, &retrcfg);

  nrf24l01_pipecfg_t pipe0 = {.en_aa = true,\
  	  	  	  	  	  	  	  .payload_length = NRF24L01_DYN_LENGTH};
  pipe0.rx_addr[0] = 0xE7;
  pipe0.rx_addr[1] = 0xE7;
  pipe0.rx_addr[2] = 0xE7;
  pipe0.rx_addr[3] = 0xE7;
  pipe0.rx_addr[4] = 0xE7;

  nrf24l01_pipecfg_t pipeDummy = {.en_aa = true,\
    	  	  	  	  	  	  	  .payload_length = NRF24L01_DYN_LENGTH};
  pipeDummy.rx_addr[0] = 0xE8;
  pipeDummy.rx_addr[1] = 0xE8;
  pipeDummy.rx_addr[2] = 0xE8;
  pipeDummy.rx_addr[3] = 0xE8;
  pipeDummy.rx_addr[4] = 0xE8;

  nrf24l01_pipecfg_t * pipes[] = {&pipe0, &pipeDummy, &pipeDummy, &pipeDummy, &pipeDummy};

  ret = ioctl(fd, NRF24L01IOC_SETPIPESCFG, pipes);

  uint8_t pipecfg = 0x01;
  ret = ioctl(fd, NRF24L01IOC_SETPIPESENABLED, &pipecfg);

  nrf24l01_datarate_t datarate = RATE_1Mbps;
  ret = ioctl(fd, NRF24L01IOC_SETDATARATE, &datarate);

  nrf24l01_crcmode_t crcmode = CRC_2BYTE;
  ret = ioctl(fd, NRF24L01IOC_SETCRCMODE, &crcmode);

  nrf24l01_state_t state = ST_RX;
  ret = ioctl(fd, NRF24L01IOC_SETSTATE, &state);

  FAR struct file *filep;
  fs_getfilep(fd, &filep);
  nrf24l01_dumpregs(filep->f_inode->i_private);

  uint8_t buffer[1];

  while(1)
  {
      ssize_t readed = read(fd, buffer, 1);
      printf("%d\n", readed);
  }

  return 0;
}
