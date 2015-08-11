#include "output_call_addr.h"

namespace libmda
{
namespace util
{
/**
 *
 **/
bool get_self_path(char buffer[], size_t size, ssize_t& len)
{
   //ssize_t len = readlink("/proc/self/exe",buffer,size-1);
   len = readlink("/proc/self/exe",buffer,size-1);
   //if(len!=-1)
   //{
   //   buffer[len] = '\0';
   //}
   //else
   //{
   //   std::cout << " no path found/buffer to small... exiting " << std::endl;
   //   abort(40);
   //}
   if(len==-1)
   {
      std::cout << " readlink returned -1 " << std::endl;
      len=0;
   }
   else if(len==size)
   {
      std::cout << " warning buffer overflow " << __FILE__ << " " << __LINE__ << std::endl;
      len=0;
   }
   buffer[len] = '\0';
   return len!=0;
}

/**
 *
 **/
bool address_to_line(void* call_addr, char* buffer, size_t size_of_buffer)
{
   if(!call_addr) return false;
   char buff[1024];
   ssize_t len; 
   if(!get_self_path(buff,sizeof(buff),len)) return false;
   const char addr2line_cmd[] = "addr2line -e";
   const char postfix_cmd[] = "";
   
   // convert address to char array
   char addr[32];
   sprintf(addr,"%p",call_addr);
   size_t addr_len = strlen(addr);
   addr[addr_len] = '\0';
   
   // allocate memory for command
   char* cmd = (char*)(malloc)(sizeof(addr2line_cmd) // command length + NULL termination
                               + len // main path
                               + sizeof(postfix_cmd) // postfix length + extra space
                               + addr_len); // address length 
   
   // make command
   strcpy(cmd,addr2line_cmd);
   strcat(cmd+sizeof(addr2line_cmd)-1,buff);
   sprintf(cmd+strlen(cmd)," %s",addr);
   strcat(cmd,postfix_cmd);
   
   size_t cmd_len = strlen(cmd);
   cmd[cmd_len]='\0';
   
   // run command
   FILE* fp = popen(cmd,"r");
   if(fp)
   {
      //char buffer[1024];
      if(fgets(buffer, size_of_buffer, fp)!=NULL)
      {
         if(buffer[0] == '?')
         {
            size_t buffer_len = strlen(buffer);
            buffer[buffer_len-1] = '\0';
            pclose(fp);
            free(cmd);
            return false;
         }
      }
      else
      {
         size_t buffer_len = strlen(buffer);
         buffer[buffer_len-1] = '\0';
         pclose(fp);
         free(cmd);
         return false;
      }
   }
   
   size_t buffer_len = strlen(buffer);
   buffer[buffer_len-1] = '\0';

   pclose(fp);
   free(cmd);
   return true;
}

/***
 * wrapper that return line for function call if it can be found or else it returns pointer
 *
 ****/
std::string wrap_address_to_line(void* call_addr)
{
   char buffer[1028];
   if(!address_to_line(call_addr, buffer, sizeof(buffer)))
   {
      return std::to_string(reinterpret_cast<std::size_t>(call_addr));
   }
   else
   {
      std::string str(buffer);
      return str;
   }
}


/**
 *
 **/
void output_call_addr(std::ostream& os, void* call_addr, char tab)
{
   os << tab << "PTR : " << call_addr << "\n";
   
   // try to find file and line (should work if debug build)
   const size_t size = 1024;
   char buff[size];
   if(address_to_line(call_addr,buff,size))
   {
      os << tab << "FILE: ";
      //output_buffer(os,buff);
      os << buff;
      os << tab << "\n";
   }
   else
   {
      os << tab << "COULD NOT DETERMINE FILE\n";
   }
}

} /* namespace util */
} /* namespace libmda */
