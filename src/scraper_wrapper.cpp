#include "scraper_wrapper.h"
#include <iostream>
#include "Document.h"

namespace hoops {

// Overriden if internal scraper needs initialization before using it.
template <class T>
bool ScraperWrapper<T>::Init() {
  return true;
}

template <class T>
void ScraperWrapper<T>::SetPage(ContentPage* content_page) {
  if (current_page_) {
    current_page_.reset(content_page);
  } else {
    current_page_ = std::unique_ptr<ContentPage>(content_page);
  }
}

template <class T>
ContentPage* ScraperWrapper<T>::CurrentPage() {
  return current_page_.get();
}

// VTable errors pop up without this.
template class ScraperWrapper<CDocument>;

}  // namespace hoops