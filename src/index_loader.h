#ifndef INDEX_LOADER_H_
#define INDEX_LOADER_H_

#include "content_loader.h"
#include "loader.h"
#include "page_reader.h"

#include <string>
#include <vector>

namespace hoops {

class IndexLoader : public ContentLoader {
 public:
  ~IndexLoader() {}
  IndexLoader() = delete;
  IndexLoader(Loader* loader, PageReader* scraper);

  ContentPage* LoadContent(const std::string& url) override;

  std::vector<ContentPage*> LoadContent(
      const std::vector<std::string>& url) override;

 private:
  // This class will not have ownership of these ptrs.
  PageReader* scraper_;
};

}  // namespace hoops

#endif  // INDEX_LOADER_H_