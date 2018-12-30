#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdint.h>

uint8_t ascll_2_int(uint8_t data)
{
    uint8_t temp = 0;
    if((data>64)&&(data<71))//A,B,C,D,E,F
    {
      temp = data - 55;
    }
    else if((data>96)&&(data<103)) //a,b,c,d,e,f
    {
      temp = data - 87;
    }
    else if((data>47)&&(data<58))
    {
      temp = data - 48;
    }
    else temp = 0;

    return temp;
}


int main(int argc, char *argv[])
{
  FILE *in;
  uint8_t  cont = 0; 
  uint8_t  data;
  uint8_t  load_hex_status = 0;
  uint32_t  i = 0;
  uint8_t  step = 0;
  uint8_t  send_buf[0xfffff];
  uint32_t start_add = 0;
  uint8_t  start_add_flag = 0;
  uint32_t buf_pt = 0;
  uint8_t  odd_even_flag = 0;
  uint32_t total_num = 0;

  in = fopen(argv[1],"r");

  while(!feof(in)) 
  { 
    if(fread((void *)&data, 1, 1, in) == 1)
    {
      switch(load_hex_status)
      {
        case 0:
           if(data == ':')
           {
              load_hex_status = 1;
           }
        break;
        case 1:
          if(data == '1')
          {
            load_hex_status = 2;
          }
          else if(data == '0')
          {
            load_hex_status = 7;
          }
        break;
        case 2:
          if(data == '0')
          {
            if(start_add_flag == 0)
            {
              load_hex_status = 3;
              start_add = 0;
              step = 0;
            }
            else
            {
              load_hex_status = 6;
              cont = 0;
              odd_even_flag = 0;
            }
          }
        break;
        case 3:
          step ++;
          start_add <<= 4;
          start_add |= ascll_2_int(data);
          
          if(step >= 4)
          {
            buf_pt = 0;
            cont = 4;
            odd_even_flag = 0;
            start_add_flag = 1;
            load_hex_status = 4;
            //printf("%x\n",start_add); 
            buf_pt = (start_add & 0xf);
          }
        break;
        case 4:
          cont ++;
          if(cont >= 7)
          {
            if(odd_even_flag == 0)
            {
              odd_even_flag = 1;
              send_buf[buf_pt] <<= 4;
              send_buf[buf_pt] |= ascll_2_int(data);
            }
            else
            {
              odd_even_flag = 0;
              send_buf[buf_pt] <<= 4;
              send_buf[buf_pt] |= ascll_2_int(data);
              //printf("%02X",send_buf[buf_pt]);
              buf_pt ++;
            }
          }
          if(cont >= 38)
          {
             load_hex_status = 5;
             
          }
          if(data == ':')
          {
            load_hex_status = 1;
            //printf("\n"); 
          }
        break;
        case 5:
          if(data == ':')
          {
            load_hex_status = 1;
            //printf("\n"); 
          }
        break;
        case 6:
         cont ++;
          if(cont >= 7)
          {
           if(odd_even_flag == 0)
            {
              odd_even_flag = 1;
              send_buf[buf_pt] <<= 4;
              send_buf[buf_pt] |= ascll_2_int(data);
            }
            else
            {
              odd_even_flag = 0;
              send_buf[buf_pt] <<= 4;
              send_buf[buf_pt] |= ascll_2_int(data);
              //printf("%02X",send_buf[buf_pt]); 
              buf_pt ++;
            }
          }
          if(cont >= 38)
          {
             load_hex_status = 5;
          }
          if(data == ':')
          {
            load_hex_status = 1;
            //printf("\n"); 
          }
        break;
        case 7:
        if(data == '1')
        {
            load_hex_status = 6;
            cont = 0;
            odd_even_flag = 0;
        }
        else
        {
            load_hex_status = 0;
        }
        break;
      }
    }
  }

  total_num = buf_pt;
  start_add &= 0xfff0;
  printf("%d,0x%X\n",total_num,start_add); 
  printf("0x%X,",start_add); 
  cont = 0;


  for(i=0;i<total_num;i++)
  {
    cont++;
    printf("%02X",send_buf[i]);
    if(cont >= 16) 
    {
      start_add += 0x10;
      printf("\n");
      printf("0x%X,",start_add);
      cont = 0;
    }
  }
  



  fclose(in);  
  printf( "\n" );
  system("pause");
  return 0;
}


