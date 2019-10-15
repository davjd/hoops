#ifndef PROFILE_LOADER_H_
#define PROFILE_LOADER_H_

#include <string>
#include <vector>

#include "content_loader.h"
#include "loader.h"
#include "page_reader.h"

namespace hoops {

class ProfileLoader : public ContentLoader {
 public:
  ~ProfileLoader() {}
  ProfileLoader() = delete;
  ProfileLoader(Loader* loader, PageReader* scraper);

  ContentPage* LoadContent(const std::string& url) override;

  std::vector<ContentPage*> LoadContent(
      const std::vector<std::string>& urls) override;

  // Read from the page and scrape it to get the metadata for a player.
  // GetPlayer(ContentPage* page);

 private:
  // This class will not have ownership of these ptrs.
  PageReader* scraper_;
};

}  // namespace hoops

#endif  // PROFILE_LOADER_H_