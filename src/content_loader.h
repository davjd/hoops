#ifndef CONTENT_LOADER_H_
#define CONTENT_LOADER_H_

#include "content_page.h"
#include "loader.h"

#include <string>
#include <vector>

namespace hoops {
class ContentLoader {
 public:
  virtual ~ContentLoader() {}
  ContentLoader() = delete;
  ContentLoader(Loader* loader) : loader_(loader) {}
  virtual ContentPage* LoadContent(const std::string& url) = 0;
  virtual std::vector<ContentPage*> LoadContent(
      const std::vector<std::string>& urls) = 0;
  Loader* loader() { return loader_; }

 private:
  // This class will not have ownership of this ptr.
  Loader* loader_;
};

}  // namespace hoops

#endif  // CONTENT_LOADER_H_