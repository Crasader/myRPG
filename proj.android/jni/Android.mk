LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

# ����Ŀ¼����Ŀ¼�ĺ���  
define walk  
    $(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call walk, $(e)))  
endef  
   
# ����ClassesĿ¼  
ALLFILES = $(call walk, $(LOCAL_PATH)/../../Classes)  
   
FILE_LIST := $(LOCAL_PATH)/hellocpp/main.cpp  
# �������ļ�����ȡ������.cpp�ļ�  
FILE_LIST += $(filter %.cpp, $(ALLFILES))
FILE_LIST += $(filter %.c, $(ALLFILES))  
   
LOCAL_SRC_FILES := $(FILE_LIST:$(LOCAL_PATH)/%=%)  


# ������ͷ�ļ�
FILE_INCLUDES := $(shell find $(LOCAL_PATH)/../../Classes -type d)
LOCAL_C_INCLUDES := $(FILE_INCLUDES) 
LOCAL_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)