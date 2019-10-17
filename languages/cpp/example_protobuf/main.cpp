/*
Copyright 2019 Aaron Chong

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include <iostream>
#include <memory>
#include <proto/example_msg.pb.h>

int main(int argc, char** argv)
{
  // Verify that the version of the library that we linked against is
  // compatible with the version of the headers we compiled against.
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  example_package::AddressBook address_book;
  
  // lets add a repeated field element
  // only when adding repeated fields will raw pointers need to be handled
  // another way is to extend the generated header and library
  example_package::Person* new_person_1 = address_book.add_people();
  new_person_1->set_name("david_1");
  new_person_1->set_id(1);

  // required fields in proto2 syntax allow us to check if the field has been
  // set
  if (new_person_1->has_high_school())
    std::cout << "without allocating, it said has, booo" << std::endl;
  else
    std::cout << "without allocating, it is considered missing, yay" << std::endl;

  // lets add another repeated field element, this time with all fields
  example_package::Person* new_person_2 = address_book.add_people();
  new_person_2->set_name("david_2");
  new_person_2->set_id(2);

  // using ownership transfer to avoid raw pointers
  auto school_msg = std::make_unique<example_package::School>();
  school_msg->set_name("Carnegie Mellon");
  school_msg->set_graduate_year(2018);
  new_person_2->set_allocated_high_school(school_msg.release());

  if (new_person_2->has_high_school())
    std::cout << "allocated, considered, nice!" << std::endl;
  else
    std::cout << "allocated, bug considered missing, =.=" << std::endl;
  
  // repeated fields can be added indefinitely
  for (int i = 0; i < 10; ++i)
  {
    // only when adding repeated fields will raw pointers need to be handled
    // another way is to extend the generated header and library
    example_package::Person* new_person = address_book.add_people();
    new_person->set_name("david");
    new_person->set_id(i);

    auto school_msg = std::make_unique<example_package::School>();
    school_msg->set_name("John Doe High");
    school_msg->set_graduate_year(2019);
    new_person->set_allocated_high_school(school_msg.release());
  }  

  // plenty of IO stuff will be added when I do use it in my projects
  
  // optional: delete all global objects allocated by libprotobuf
  google::protobuf::ShutdownProtobufLibrary();
  
  return 0;
}
