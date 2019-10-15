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

// This file is currently used to determine design of current and future objects
// (and program flow).

// static size_t WriteCallback(void* contents, size_t size, size_t nmemb,
//                             void* userp) {
//   ((std::string*)userp)->append((char*)contents, size * nmemb);
//   return size * nmemb;
// }

// class PageVerifier {
//  public:
//   // Methods that will verify which type of page we're reading.
//   bool IsProfilePage();
//   bool IsIndexPage();
// };

// class Env {
//  public:
//   std::unique_ptr<PageReader> p;
// };

class Parser {
 public:
  virtual ~Parser() { std::cout << "deleting inside Parser.\n"; }
  Parser() {}
  virtual bool Parse(CDocument* doc) = 0;
};

//~BBallReferencePage() {}

void GetPlayersMetadata(CDocument* doc) {
  // std::string result = "";
  CSelection sel = doc->find("div#info");
  if (sel.nodeNum() == 0) {
    std::cout << "isempty()\n";
    return;
  } else {
    std::cout << "there exists " << sel.nodeNum()
              << " findings with such query..\n";
  }

  CNode table = sel.nodeAt(0);
  std::cout << table.text() << "\n";
  // for (int i = 0; i < table.childNum(); ++i){
  //   CNode tr = table.childAt(i);
  //   if (tr.attribute("class") == "thead") continue;

  //   CSelection header_selection = tr.find("th");
  //   if (header_selection.nodeNum() == 0) continue;

  //   CNode header = header_selection.nodeAt(0);
  //   CNode header_child = header.childAt(0);
  //   std::cout << "player: " << header.text() << ": "
  //     << (header_child.tag() == "a" ? header_child.attribute("href") :
  //     header_child.childAt(0).attribute("href"))
  //     << "\n";

  //   CSelection cells = tr.find("td");
  //   for (int j = 0; j < cells.nodeNum(); ++j){
  //     CNode cell = cells.nodeAt(j);
  //     std::cout << cell.attribute("data-stat") << " : " << cell.text() << (j
  //     == cells.nodeNum() - 1 ? "" : ", ");
  //   }
  //   std::cout << "\n";
  // }
  // return result;
}

int main() {
  // std::this_thread::sleep_for(std::chrono::seconds(3));

  // HoopsEnvironment<GumboScraper> env = HoopsEnvironment::Get();

  // HoopsEnvironment env = HoopsEnvironment::Get();
  // env->SetScraper(new GumboScraper());
  // SetScraper would need to take scraper interface or template, but doing
  // template brings us to the first issue.

  // HoopsContext<CDocument> env(new GumboScraper());
  // auto scraper = env.scraper();
  // std::cout << env.LoadPlayerFiles(false) << "\n";

  // Hoops::Options options;
  // options.scraper = new GumboScraper();
  // env.scraper = WrapperScraper();
  // WrapperScraper.internal_scraper = new GumboScraper();

  auto env =
      std::make_unique<hoops::HoopsEnvironment>(new hoops::GumboScraper());

  // env::ContentLoader.GetPage()
  // player = env::PlayerLoader.GetPlayer(full_name);
  // std::cout << env->PlayerProfileUrl("/players/l/labissk01.html") << " with
  // player letter " <<
  // Loader::GetPlayerLetter(env->PlayerProfileUrl("/players/l/labissk01.html"))
  // << ": " <<
  // env->loader()->DoesPlayerUrlExist(env->PlayerProfileUrl("/players/l/labissk01.html"))
  // << "\n";
  bool init_status = env->Init();
  if (!init_status) {
    std::cout << "Error initializing environment.\n";
    return 0;
  }
  std::cout << "Finished: " << env->Alphabet() << "\n\n";

  // GetPlayersMetadata(
  //     dynamic_cast<hoops::GumboScraper*>(env->scraper())->scraper());
  auto player = env->GetPlayer("Carmelo Anthony");
  std::cout << "Getting content for " << player.GetFullName() << " with url "
            << player.GetFullUrl() << "\n";
  auto page =
      new hoops::BBallReferencePage(env->GetPage(player), player.GetFullUrl());

  std::cout << page->GetPageType() << "\n";
  auto g_scraper = static_cast<hoops::GumboScraper*>(env->scraper());
  g_scraper->SetPage(page);
  std::cout << g_scraper->FillPlayerMetadata(&player) << "\n";
  std::cout << "file: "
            << hoops::env::filename::ProfileFileName(player.GetFullUrl())
            << "\n";

  // Figure out how to set page to scraper, then scraper will get metadata.
  // Maybe have class to do this that will explicitly have gumbo scraper.
  // env->scraper()->SetPage(page.get());

  // std::cout << hoops::env::PlayersIndexUrl('a') << "\n";
  // std::cout << hoops::env::PlayerProfileUrl("/players/z/hello.html") << "\n";

  // env->FillPlayerMetadata(player);
  // env->Copy();
  // auto gumbo_scraper = dynamic_cast<GumboScraper*>(env->scraper());
  // const std::string page =
  // env->loader()->GetContent("https://www.basketball-reference.com/players/z/");
  // gumbo_scraper->SetPage(page);
  // std::cout << "Players: " << gumbo_scraper->GetPlayerNames() << "\n";
  // std::cout << GetPlayersMetadata(gumbo_scraper->GetScraper()) << "\n";
  // PlayerMetadata p = gumbo_scraper->GetPlayer("Gary Zeller");
  // std::cout << "Player gotten: " << p.first_name() << "with link: " <<
  // p.url() << "\n";

  // Env env;
  // env.p = std::make_unique<GScraper>();
  // std::cout << "body: " << env.p->GetBody() << "\n";
  // CDocument doc;
  // Loader loader;

  // loader.RemoveReferenceFiles();

  // const std::string base_url = "https://www.basketball-reference.com";
  // const std::string kAlphabet = "abcdefghijklmnopqrstuvyz";

  // loader.Load(base_url + "/players/f/");

  // std::string page = loader.Retrieve();
  // doc.parse(page.c_str());
  // CSelection sel = doc.find("table#players tbody");

  // if (sel.nodeNum() == 0){
  //   std::cout << "no elements\n";
  //   return 0;
  // }
  // std::cout << sel.nodeAt(0).text();
  // std::unique_ptr<hoops::Loader> loader = std::make_unique<hoops::Loader>();
  // std::cout
  //     << "filename: "
  //     << hoops::env::filename::ProfileFileName(
  //            "https://www.basketball-reference.com/players/a/anderda01.html")
  //     << "\n";
  // std::cout
  //     << loader->DoesPlayerUrlExist(
  //            "https://www.basketball-reference.com/players/a/anderda01.html")
  //     << "\n";

  return 0;
}