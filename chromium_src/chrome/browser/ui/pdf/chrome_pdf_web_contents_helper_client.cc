// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "chrome/browser/ui/pdf/chrome_pdf_web_contents_helper_client.h"

#include "extensions/browser/guest_view/mime_handler_view/mime_handler_view_guest.h"

namespace {

content::WebContents* GetWebContentsToUse(content::WebContents* web_contents) {
  // If we're viewing the PDF in a MimeHandlerViewGuest, use its embedder
  // WebContents.
  auto* guest_view =
      extensions::MimeHandlerViewGuest::FromWebContents(web_contents);
  if (guest_view)
    return guest_view->embedder_web_contents();
  return web_contents;
}

}  // namespace

ChromePDFWebContentsHelperClient::ChromePDFWebContentsHelperClient() {}

ChromePDFWebContentsHelperClient::~ChromePDFWebContentsHelperClient() {}

void ChromePDFWebContentsHelperClient::UpdateContentRestrictions(
    content::WebContents* contents,
    int content_restrictions) {}

void ChromePDFWebContentsHelperClient::OnPDFHasUnsupportedFeature(
    content::WebContents* contents) {}

void ChromePDFWebContentsHelperClient::OnSaveURL(
    content::WebContents* contents) {}
