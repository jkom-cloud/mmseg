# -*- coding: utf-8 -*-
import  ctypes

mmseg = ctypes.CDLL("../libs/libmmseg.so")
instance  = mmseg.getInstance()
mmseg.loadDict(instance, "../data/words.dic")
s = mmseg.copySegs(instance, "双侧乳腺轻度小叶增生伴左乳结节")
data = ctypes.string_at(s, -1).decode("utf-8")
mmseg.releaseSegs(s)
print(data)
mmseg.unloadDict(instance)
mmseg.delInstance(instance)
