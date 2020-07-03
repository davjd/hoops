#ifndef GUMBO_SCRAPER_H_
#define GUMBO_SCRAPER_H_

#include <string>

#include <memory>
#include "Document.h"
#include "Node.h"
#include "bball_page.h"
#include "meta_section_parser.h"
#include "page_reader.h"
#include "player_extractor.h"
#include "player_metadata.h"
#include "scraper_wrapper.h"
#include "stats_adapters.h"

class CDocument;

namespace hoops {

class GumboScraper : public ScraperWrapper<CDocument>, public PlayerExtractor {
 public:
  ~GumboScraper() {}
  explicit GumboScraper(CDocument* scraper);
  GumboScraper();
  void SetPageContent(const std::string& content,
                      const std::string& url = "") override;
  void SetPage(ContentPage* page) override;

  // Gets <body> tag of HTML page.
  std::string GetBody() override;

  // Checks if current page is empty.
  bool IsEmpty() override;
  std::string GetPlayerNames() override;
  std::vector<PlayerMetadata> GetPlayers() override;
  PlayerMetadata GetPlayer(const std::string& player_name) override;
  bool FillPlayerMetadata(PlayerMetadata* mutable_player) override;
  void FillMetaSection(PlayerMetadata* mutable_player, CNode selection);
  void FillBadgeData(PlayerMetadata* mutable_player, CNode badge_section);
  void FillUniformData(PlayerMetadata* mutable_player, CNode badge_section);
  void FillStatsData(PlayerMetadata* mutable_player, CNode badge_section);
  bool FillNumbers(PlayerMetadata* mutable_player);

  BBallReferencePage::PageType page_type() { return page_type_; }

  BBallReferencePage::PageType page_type_;

 private:
  std::unique_ptr<MetaSectionParser> meta_parser_;
  std::unique_ptr<StatsAdapters> adapters_;
};

}  // namespace hoops
#endif  // GUMBO_SCRAPER_H_