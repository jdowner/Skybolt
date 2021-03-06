/* Copyright 2012-2020 Matthew Reid
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "EngineCommandLineParser.h"

#include <SkyboltCommon/Json/ReadJsonFile.h>
#include <boost/optional.hpp>
#include <boost/log/trivial.hpp>

namespace po = boost::program_options;

namespace skybolt {

boost::program_options::variables_map EngineCommandLineParser::parse(int argc, char** argv)
{
	boost::program_options::options_description desc;
	EngineCommandLineParser::addOptions(desc);
	return EngineCommandLineParser::parse(argc, argv, desc);
}

po::variables_map EngineCommandLineParser::parse(int argc, char** argv, const po::options_description& desc)
{
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);
	return vm;
}

void EngineCommandLineParser::addOptions(po::options_description& desc)
{
	desc.add_options()
		("help", "produce help message")
		("settingsFile", po::value<std::string>(), "settings file");
}

boost::optional<nlohmann::json> EngineCommandLineParser::readSettings(const boost::program_options::variables_map& params)
{
	if (params.count("settingsFile"))
	{
		std::string settingsFilename = params["settingsFile"].as<std::string>();
		BOOST_LOG_TRIVIAL(warning) << "Reading settings file '" << settingsFilename << "'";
		return readJsonFile(settingsFilename);
	}
	return boost::none;
}

} // namespace skybolt