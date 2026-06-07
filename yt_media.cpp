#include <cstdlib>
#include <iostream>
#include <regex>
#include <string>

/*
 yt-dlp c++ downloading cotent directly from youtube
 @Kēād çōdēs
 */

constexpr const char *Red = "\033[1;31m";
constexpr const char *Green = "\033[1;32m";
constexpr const char *Yellow = "\033[1;33m";
constexpr const char *Blue = "\033[1;34m";
constexpr const char *Mangenta = "\033[1;35m";
constexpr const char *Cyan = "\033[1;36m";
constexpr const char *Reset = "\033[0m";

int menu() {
  bool valid = false;
  int choice = 1;
  do {
    std::cout << Cyan << "===============================\n"
              << Green << "\tKEAD MEDIA TOWER\n"
              << Cyan << "===============================\n"
              << Blue << "\n1. Audio(mp3)\n2. Video(mp4)\n"
              << "3. Exit\n"
              << Reset << "Option :";
    if ((std::cin >> choice) && choice > 0 && choice < 4)
      valid = 1;
    else {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      continue;
    }
  } while (!valid);
  return choice;
}

int main() {
  std::regex pattern("https?:\\/\\/(www\\.)?(youtube\\.com|youtu\\.be)\\/.+");
  std::string url, cmd;

  std::cout << Red << "Enter url :" << Reset;
  std::getline(std::cin, url);
  std::cin.clear();

  if (!(std::regex_match(url, pattern))) {
    std::cerr << Red << "Invalid url...\n";
    std::cout << Mangenta << "\nGoodbye 👋\n";

    return EXIT_FAILURE;
  }

  int choice = menu();

  if (choice == 1) {
    std::cout << Yellow << "\n🎧 Audio ::\n\n" << Reset;
    cmd = "yt-dlp --remote-components ejs:github --js-runtimes node -x "
          "--audio-format mp3 -o "
          "\"/storage/emulated/0/Download/kead_jams/%(title)s.%(ext)s\" \"" +
          url + "\"";
  } else if (choice == 2) {
    bool valid = false, subtitles;
    int res = 1;
    std::cout << Yellow << "\n🎬 Video resolutions ::\n"
              << Reset << "\n1. 360p\n2. 720p\n3. 1080p\n"
              << "4. Best Available\n"
              << Yellow << "\nChoice :" << Reset;
    if (std::cin >> res && res > 0 && res < 5)
      valid = true;

    if (!valid) {
      std::cerr << Red << "Invalid input...\n\n";
      std::cout << Mangenta << "Goodbye 👋\n";

      return EXIT_FAILURE;
    }

    switch (res) {
    case 1: {
      cmd = "yt-dlp --remote-components ejs:github --js-runtimes node -o "
            "\"/storage/emulated/0/Download/kead_vids/%(title)s.%(ext)s\" -f "
            "\"bv*[height<=360]+ba\" --merge-output-format mp4 \"" +
            url + "\"";
      break;
    }
    case 2: {
      cmd = "yt-dlp --remote-components ejs:github --js-runtimes node -o "
            "\"/storage/emulated/0/Download/kead_vids/%(title)s.%(ext)s\" -f "
            "\"bv*[height<=720]+ba\" --merge-output-format mp4 \"" +
            url + "\"";
      break;
    }
    case 3: {
      cmd = "yt-dlp --remote-components ejs:github --js-runtimes node -o "
            "\"/storage/emulated/0/Download/kead_vids/%(title)s.%(ext)s\" -f "
            "\"bv*[height<=1080]+ba\" --merge-output-format mp4 \"" +
            url + "\"";
      break;
    }
    case 4: {
      cmd = "yt-dlp --remote-components ejs:github --js-runtimes node -o "
            "\"/storage/emulated/0/Download/kead_vids/%(title)s.%(ext)s\" -f "
            "\"bv*+ba\" --merge-output-format mp4 \"" +
            url + "\"";
      break;
    }
    default:
      std::cerr << Red << "Invalid input...\n\n";
      std::cout << Mangenta << "\nGoodbye 👋\n";
    }

  } else {
    std::cout << Mangenta << "\nGoodbye 👋\n";
  }

  if (!url.empty())
    system(cmd.c_str());

  return EXIT_SUCCESS;
}
