#ifndef PAGE_READER_H_
#define PAGE_READER_H_

#include "content_page.h"

#include <memory>
#include <string>

namespace hoops {

class PageReader {
 public:
  virtual ~PageReader() {}
  // Gets <body> tag of HTML page.
  virtual std::string GetBody() = 0;

  // Checks if current page is empty.
  virtual bool IsEmpty() = 0;

  // Page content passed to some scraper.
  virtual void SetPageContent(const std::string& content,
                              const std::string& url = "") = 0;

  // Page passed to some scraper implementation.
  virtual void SetPage(ContentPage* page) = 0;

  virtual ContentPage* CurrentPage() = 0;
};

}  // namespace hoops

#endif  // PAGE_READER_H_