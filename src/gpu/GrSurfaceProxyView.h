/*
 * Copyright 2019 Google LLC
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef GrSurfaceProxyView_DEFINED
#define GrSurfaceProxyView_DEFINED

#include "include/core/SkRefCnt.h"
#include "include/gpu/GrTypes.h"
#include "src/gpu/GrSurfaceProxy.h"
#include "src/gpu/GrSwizzle.h"

class GrSurfaceProxyView {
public:
    GrSurfaceProxyView() = default;

    GrSurfaceProxyView(sk_sp<GrSurfaceProxy> proxy, GrSurfaceOrigin origin, GrSwizzle swizzle)
            : fProxy(proxy), fOrigin(origin), fSwizzle(swizzle) {}

    // This entry point is used when we don't care about the origin or the swizzle.
    GrSurfaceProxyView(sk_sp<GrSurfaceProxy> proxy)
            : fProxy(proxy), fOrigin(kTopLeft_GrSurfaceOrigin) {}

    GrSurfaceProxyView(GrSurfaceProxyView&& view) = default;
    GrSurfaceProxyView(const GrSurfaceProxyView&) = delete;

    GrSurfaceProxyView& operator=(const GrSurfaceProxyView& that) = default;

    bool operator==(const GrSurfaceProxyView& view) {
        return fProxy.get() == view.fProxy.get() &&
               fOrigin == view.fOrigin &&
               fSwizzle == view.fSwizzle;
    }
    bool operator!=(const GrSurfaceProxyView& other) { return !(*this == other); }

    GrSurfaceProxy* proxy() const { return fProxy.get(); }
    GrTextureProxy* asTextureProxy() const { return fProxy->asTextureProxy(); }
    GrRenderTargetProxy* asRenderTargetProxy() const { return fProxy->asRenderTargetProxy(); }

    GrSurfaceOrigin origin() const { return fOrigin; }
    const GrSwizzle& swizzle() const { return fSwizzle; }

    void reset() {
        *this = {};
    }

private:
    sk_sp<GrSurfaceProxy> fProxy;
    GrSurfaceOrigin fOrigin = kTopLeft_GrSurfaceOrigin;
    GrSwizzle fSwizzle;
};

#endif
