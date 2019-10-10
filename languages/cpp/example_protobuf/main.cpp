#include <iostream>
#include <proto/example_msg.pb.h>


int main(int argc, char** argv)
{
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  example_package::AddressBook address_book;

  for (int i = 0; i < 10; ++i)
  {
    example_package::Person* new_person = address_book.add_people();
    new_person->set_name("david");
    new_person->set_id(i);
  }  
  
  // optional: delete all global objects allocated by libprotobuf
  google::protobuf::ShutdownProtobufLibrary(); 
  
  return 0;
}
