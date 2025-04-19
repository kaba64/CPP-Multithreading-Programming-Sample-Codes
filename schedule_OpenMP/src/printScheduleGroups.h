template<typename Container>
void printSchedule(const Container& c, const std::string& type) {
  std::cout << "Scheduling type : " << type << "\n";

  for (int i = 0; i < static_cast<int>(c.size()) && !c[i].empty(); ++i) {
    std::cout << "---------Thread : " << i << "----------\n";
    int chunk = c[i][0].first;
    std::cout << "\nchunk : " << chunk << "\n";
    int count = 0;

    for (int j = 0; j < static_cast<int>(c[i].size()); ++j) {

      std::cout << c[i][j].second << "\t";
      ++count;

      if(count==chunk){
        count = 0;
        if(j<static_cast<int>(c[i].size() - 1)){ /*check do not try to access out of range*/
          chunk = c[i].at(j+1).first;
	  /*This part is needed to sure the actual chunk size is used for the
	   static and dynamic scheduling if the size of last iteration is smaller
	  than chunk_sch in the source code*/
	  chunk = (chunk+j)<static_cast<int>(c[i].size()) ? chunk : (c[i].size()-j-1);
          std::cout << "\n\nchunk : " << chunk << "\n";
        }
      }else if (count % 12 == 0) {
        std::cout << "\n";
      }
    }
    std::cout << "\n\n";
  }
}
