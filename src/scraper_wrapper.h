#ifndef SCRAPER_WRAPPER_H_
#define SCRAPER_WRAPPER_H_

#include <memory>
#include "content_page.h"
#include "page_reader.h"

namespace hoops {

template <class T>
class ScraperWrapper : public PageReader {
 public:
  // Getter for class that implements this interface and contains actual
  // scraper object.
  ~ScraperWrapper() {}
  T* scraper() { return scraper_.get(); }
  void set_scraper(T* scraper) { scraper_ = std::unique_ptr<T>(scraper); }

  // Overriden if internal scraper needs initialization before using it.
  bool Init();
  void SetPage(ContentPage* content_page) override;
  ContentPage* CurrentPage() override;

 protected:
  std::unique_ptr<T> scraper_;
  std::unique_ptr<ContentPage> current_page_;
};

}  // namespace hoops

#endif  // SCRAPER_WRAPPER_H_