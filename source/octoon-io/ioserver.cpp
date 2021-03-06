// File: IoServer.cpp
// Author: PENGUINLIONG
#include <cassert>
#include <algorithm>
#include "octoon/io/ioserver.h"

namespace octoon
{
	namespace io
	{
		OctoonImplementSingleton(IoServer);

		void
		IoServer::mount_archive(const std::string& vpath, const archive_pointer& vdir)
		{
			registry_.insert(std::make_pair(vpath, vdir));
		}

		void
		IoServer::mount_archive(const std::string& vpath, archive_pointer&& vdir)
		{
			registry_.insert(std::make_pair(vpath, std::move(vdir)));
		}

		void
		IoServer::mount_archive(std::string&& vpath, archive_pointer&& vdir)
		{
			registry_.insert(std::make_pair(std::move(vpath), std::move(vdir)));
		}

		archive_pointer
		IoServer::unmount_archive(const std::string& vdir)
		{
			auto it = registry_.find(vdir);
			auto ptr = std::move(it->second);
			registry_.erase(it);
			return ptr;
		}

		archive_pointer
		IoServer::get_archive(const Orl& orl) const
		{
			auto it = registry_.find(orl.virtual_dir());
			return it != registry_.end() ?  it->second : nullptr;
		}
	}
}