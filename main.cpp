#include <functional>
#include <iostream>
#include <memory>
#include <string>

#include "bball_page.h"
#include "content_page.h"
#include "env_namespace.h"
#include "gumbo_scraper.h"
#include "hoops_env.h"
#include "loader.h"

#include "Document.h"
#include "Node.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

// usage:
//

class MyApp : public wxApp {
 public:
  virtual bool OnInit();
};

int main() {
  auto env =
      std::make_unique<hoops::HoopsEnvironment>(new hoops::GumboScraper());
  bool init_status = env->Init();
  if (!init_status) {
    std::cout << "Error initializing environment.\n";
    return 0;
  }
  std::cout << "Finished: " << env->Alphabet() << "\n\n";

  auto player = env->GetPlayer("Carmelo Anthony");
  std::cout << "Getting content for " << player.GetFullName() << " with url "
            << player.GetFullUrl() << "\n";
  auto page =
      new hoops::BBallReferencePage(env->GetPage(player), player.GetFullUrl());
  auto g_scraper = static_cast<hoops::GumboScraper*>(env->scraper());
  g_scraper->SetPage(page);
  if (!g_scraper->FillPlayerMetadata(&player)) {
    std::cout << "Error filling metadata.\n";
  }

  if (!g_scraper->FillNumbers(&player)) {
    std::cout << "Error filling metadata.\n";
  }
  std::cout << "file: "
            << hoops::env::filename::ProfileFileName(player.GetFullUrl())
            << "\n";
  return 0;
}