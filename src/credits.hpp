// Copyright (c) 2026 Tom Iwan
// PERMISSION IS HEREBY GARANTED TO ANYONE TO DO ANYTHING WITH THIS SHIT EXEPT FOR THE USE IN PROJECTS ACCUMULATING CAPITAL
// THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND.

#pragma once

#include <format>
#include <fstream>
#include <string>

#ifdef JSON_INCLUDE_PATH
	#include JSON_INCLUDE_PATH
#else
	#include "../vendor/json.hpp"
#endif

using json = nlohmann::json;

namespace Credits
{
	static constexpr const std::string COLLECTIONS_KEY {"credits"};
	static constexpr const std::string COLLECTION_TITLE_KEY {"title"};
	static constexpr const std::string COLLECTION_CREDIT_MEMBERS_KEY {"members"};
	static constexpr const std::string CREDIT_TITLE_KEY {"title"};
	static constexpr const std::string CREDIT_AUTHOR_KEY {"author"};
	static constexpr const std::string CREDIT_DESC_KEY {"desc"};

	struct Credit
	{
		std::string title {};
		std::string author {};
		std::string desc {};
	};

	struct Collection
	{
		std::string title {};
		std::vector <Credit> credits {};
	};

	class CreditContainer
	{
	public:
		CreditContainer();
		CreditContainer(const std::string &path);
		~CreditContainer();
		void Init(const std::string &path);
		std::vector<Collection> collections {};
	};

	#ifdef CREDITS_HPP_IMPL

	CreditContainer::CreditContainer()
	{}

	CreditContainer::CreditContainer(const std::string &path)
	{
		Init(path);
	}

	CreditContainer::~CreditContainer()
	{}

	void CreditContainer::Init(const std::string &path)
	{
		std::ifstream f(path);

        if(!f.is_open())
        {
            std::runtime_error(std::format("[CREDITS_HPP ERROR] failed to load file '{}'", path));
        }

		json j;
		f >> j;

		for(auto jCollection : j[COLLECTIONS_KEY])
		{
			Collection collection {};
			collection.title = jCollection[COLLECTION_TITLE_KEY];

			for(auto jCredit : jCollection[COLLECTION_CREDIT_MEMBERS_KEY])
			{
				Credit credit {};
				credit.title = jCredit[CREDIT_TITLE_KEY];
				credit.author = jCredit[CREDIT_AUTHOR_KEY];
				credit.desc = jCredit[CREDIT_DESC_KEY];
				collection.credits.push_back(credit);
			}
			collections.push_back(collection);
		}
	}
	#endif
};
