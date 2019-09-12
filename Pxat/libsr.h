#ifndef _LIB_SCHNORR_H_
#define _LIB_SCHNORR_H_

#define PUB_KEY_LEN             32
#define PRI_KEY_LEN             64
#define SIGN_LEN                64
#define BUFFER_LEN              96

#define STATUS_OK               0
#define STATUS_NOK              1
#define ERR_KEYPAIR             2
#define ERR_PRIKEY              3
#define ERR_SIGBYTE             4


unsigned int sr_sign(unsigned char* message,unsigned int len,unsigned char* random,unsigned char* keypair, unsigned char* sign_out);

#endif
