#pragma once

#include <json/reader.h>
#include "fin/io/file.h"
#include "fin/io/filereader.h"
#include "savedata.h"

class SaveReader {
  public:
  SaveData load( fin::io::File file ) {
    fin::io::FileReader fileReader( file );
    std::string fileText = fileReader.read_all_and_close();

    Json::Value root;
    jsonReader.parse( fileText, root, false );

    SaveData saveData;
    Json::Value::Members members = root.getMemberNames();
    
  }

  private:
  Json::Reader jsonReader;
};
