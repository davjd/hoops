#ifndef BBALL_PAGE
#define BBALL_PAGE

#include <string>
#include "content_page.h"

namespace hoops {

class BBallReferencePage : public ContentPage {
 public:
  enum PageType {
    kNoPage,
    kInvalidPage,
    kPageNotSupported,
    kIndexPage,
    kProfilePage,
    kCoachPage,  // Below ones aren't implemented yet, maybe in the future.
    kCollegePage,
  };

  ~BBallReferencePage() {}
  BBallReferencePage() = delete;
  BBallReferencePage(const std::string& content, const std::string& url,
                     PageType page_type);
  explicit BBallReferencePage(const std::string& content,
                              const std::string& url);
  bool IsValidPage() override;
  std::string Url() override;
  bool HasPlayerProfilePage();
  bool HasIndexPage();
  bool HasNoPage();
  void set_page_type() { page_type_ = GetPageType(); }

  // Return the type of page this is, by looking at the type of url this page
  // belongs to.
  PageType GetPageType();
  PageType page_type() { return page_type_; }

 private:
  PageType page_type_;
  const std::string current_url_;
};

}  // namespace hoops

#endif  // BBALL_PAGE