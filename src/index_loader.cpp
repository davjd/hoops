#include "index_loader.h"
#include "bball_page.h"
#include "env_namespace.h"

namespace hoops {

IndexLoader::IndexLoader(Loader* loader, PageReader* scraper)
    : ContentLoader(loader), scraper_(scraper) {}

ContentPage* IndexLoader::LoadContent(const std::string& url) {
  // this will ultimately require moving some of the FileName makers into a
  // more defined class. either the env class or loader class. OR we can
  // simply move the FILENAME methods inside one single file without any
  // ownership class, only being owned by a namespace. OR have a struct inside
  // the ENV class.
  // loader_->Load();
  bool load_successful = loader()->Load(url, true, env::filename::IndexFileName,
                                        Loader::DoesIndexFileExist);
  if (!load_successful) {
    return nullptr;
  }
  const std::string page_content = loader()->Retrieve();
  return new BBallReferencePage(page_content, url);
}

std::vector<ContentPage*> IndexLoader::LoadContent(
    const std::vector<std::string>& urls) {
  std::vector<ContentPage*> pages;
  for (const std::string& profile_url : urls) {
    ContentPage* page = LoadContent(profile_url);
    if (page == nullptr) continue;
    pages.push_back(page);
  }
  return pages;
}
}  // namespace hoops