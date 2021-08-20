#include "../auth/auth.h"

static int writerFunction(char* data, size_t size, size_t nmemb, std::string* writerData) {

	if (writerData == NULL)
		return 0;
	writerData->append(data, size * nmemb);

	return size * nmemb;
}

std::string Login(std::string uname, std::string hwid) {

	// POST //

	CURL* curl = nullptr;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (curl) {

		std::string path = "https://xmasterpanel.xyz/spfiles/login.php?username=";

		curl_easy_setopt(curl, CURLOPT_URL, path.c_str());
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "username=" + uname + "&hwid=" + hwid);

		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			MessageBoxA(0, "liberror", 0, 0);
			return "-";
		}
		curl_easy_cleanup(curl);



	}
	curl_global_cleanup();



	// READ //



	std::string response;
	std::string path = "https://xmasterpanel.xyz/spfiles/login.php?username=" + uname + "&hwid=" + hwid;


	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (curl) {

		curl_easy_setopt(curl, CURLOPT_URL, path.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writerFunction);
		CURLcode code = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

	}
	curl_global_cleanup();

	return response;


}

std::string tester_check() {

	// POST //

	CURL* curl = nullptr;
	CURLcode res;

	std::string path = "http://xmasterpanel.xyz/test.php";

	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (curl) {



		curl_easy_setopt(curl, CURLOPT_URL, path.c_str());

		res = curl_easy_perform(curl);

		if (res != CURLE_OK) {
			MessageBoxA(0, "ERROR", 0, 0);
			return "-";
		}
		curl_easy_cleanup(curl);



	}
	curl_global_cleanup();



	// READ //


	std::string response3;



	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	if (curl) {

		curl_easy_setopt(curl, CURLOPT_URL, path.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response3);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writerFunction);
		CURLcode code = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

	}
	curl_global_cleanup();

	return response3;
}