#include "bball_page.h"
#include <iostream>
#include "env_namespace.h"

namespace hoops {

BBallReferencePage::BBallReferencePage(const std::string& content,
                                       const std::string& url,
                                       PageType page_type)
    : ContentPage(content), current_url_(url), page_type_(page_type) {}

BBallReferencePage::BBallReferencePage(const std::string& content,
                                       const std::string& url)
    : ContentPage(content),
      current_url_(url),
      page_type_(PageType::kInvalidPage) {}

bool BBallReferencePage::IsValidPage() { return true; }

bool BBallReferencePage::HasPlayerProfilePage() {
  return page_type_ == PageType::kProfilePage;
}

bool BBallReferencePage::HasIndexPage() {
  return page_type_ == PageType::kIndexPage;
}

bool BBallReferencePage::HasNoPage() { return page_type_ == PageType::kNoPage; }

// Return the type of page this is, by looking at the type of url this page
// belongs to.
BBallReferencePage::PageType BBallReferencePage::GetPageType() {
  // Get the url of this page, which should be in the first line of the page.

  // Check that the url has the correct base url (bbal reference home link).
  const std::string& url = Url();
  auto base_url_pos = url.find(env::url::kBaseUrl);
  if (base_url_pos == std::string::npos || base_url_pos != 0) {
    std::cout << "incorrect base url.\n";
    return PageType::kInvalidPage;
  }
  // Check that the url has a correct entity section (for now only players,
  // but maybe in the future we'll add coaches etc).
  std::string tail = url.substr(base_url_pos + env::url::kBaseUrl.size());
  auto section_pos = tail.find(env::url::kPlayersUrlSection);
  if (section_pos == std::string::npos) {
    // This page doesn't deal with players. Could be extended in the future to
    // include coach/NCAA pages, but for now we'll only support player pages.
    std::cout << "page not supported.\n";
    return PageType::kPageNotSupported;
  }

  // Since this url has the players section, it also needs to have a letter
  // (e.g. 'players/a/...') to be a valid page.
  tail = tail.substr(section_pos +
                     std::string(env::url::kPlayersUrlSection).size());
  if ((tail.size() < 2) || !std::isalpha(tail[0]) || !(tail[1] == '/')) {
    std::cout << "incorrect tail after player section.\n";
    return PageType::kInvalidPage;
  }

  // If the url doesn't have anything else, then this is a players index page.
  if (tail.size() == 2) return PageType::kIndexPage;

  // Now see if the url is a profile page url, by seeing that it has a
  // username (alphanumeric) followed by a period ('.') and 'html'.
  tail = tail.substr(2);
  auto it = std::find_if(tail.begin(), tail.end(), [](char character) {
    return !std::isalnum(character);
  });

  // If it doesn't have the period, this url is invalid.
  if (it == tail.end() || *it != '.') {
    std::cout << "period missing.\n";
    return PageType::kInvalidPage;
  }

  // Now check that it ends with 'html', we'll keep using the iterator since
  // we already have it in memory.
  const std::string html_frmt = "html";
  for (int i = 0; i < html_frmt.size(); ++i) {
    if (it == tail.end() || *++it != html_frmt[i]) {
      std::cout << "doesn't follow html format.\n";
      return PageType::kInvalidPage;
    }
  }
  return PageType::kProfilePage;
}

std::string BBallReferencePage::Url() { return current_url_; }

bool BBallReferencePage::IsProfilePage(PageType page_type) {
  return page_type == PageType::kProfilePage;
}

bool BBallReferencePage::IsIndexPage(PageType page_type) {
  return page_type == PageType::kIndexPage;
}

}  // namespace hoops