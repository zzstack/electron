// Copyright (c) 2015 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef ATOM_BROWSER_ATOM_RESOURCE_DISPATCHER_HOST_DELEGATE_H_
#define ATOM_BROWSER_ATOM_RESOURCE_DISPATCHER_HOST_DELEGATE_H_

#include <string>

#include "content/public/browser/resource_dispatcher_host_delegate.h"
#include "electron/buildflags/buildflags.h"

namespace atom {

class AtomResourceDispatcherHostDelegate
    : public content::ResourceDispatcherHostDelegate {
 public:
  AtomResourceDispatcherHostDelegate();
  ~AtomResourceDispatcherHostDelegate() override;

  // content::ResourceDispatcherHostDelegate:
  bool ShouldInterceptResourceAsStream(net::URLRequest* request,
                                       const std::string& mime_type,
                                       GURL* origin,
                                       std::string* payload) override;

  void OnStreamCreated(net::URLRequest* request,
                       std::unique_ptr<content::StreamInfo> stream) override;

 private:
  DISALLOW_COPY_AND_ASSIGN(AtomResourceDispatcherHostDelegate);

#if BUILDFLAG(ENABLE_PDF_VIEWER)
  struct StreamTargetInfo {
    std::string extension_id;
    std::string view_id;
  };

  std::map<net::URLRequest*, StreamTargetInfo> stream_target_info_;
#endif
};

}  // namespace atom

#endif  // ATOM_BROWSER_ATOM_RESOURCE_DISPATCHER_HOST_DELEGATE_H_
