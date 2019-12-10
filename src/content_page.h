#ifndef CONTENT_PAGE_H_
#define CONTENT_PAGE_H_

#include <string>
#include <iostream>

namespace hoops {

class ContentPage {
 public:
  virtual ~ContentPage() {
  }
  ContentPage() = delete;
  explicit ContentPage(const std::string& content) : content_(content) {}

  // Returns whether the held page is a valid page (has the correct content for
  // the class representing the type of page).
  virtual bool IsValidPage() = 0;
  virtual std::string Url() = 0;
  std::string content() { return content_; }

 private:
  const std::string content_;
};

}  // namespace hoops
#endif  // CONTENT_PAGE_H_