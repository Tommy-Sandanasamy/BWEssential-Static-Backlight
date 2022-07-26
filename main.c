#include "main.h"


int main(){
	hid_init();
	
	struct hid_device_info *ll;

	ll = hid_enumerate(0x1532, 0x0237);

	while(ll){
		if(ll->usage_page == 0x01 && ll->usage == 0x02 && ll->interface_number == 0x02){
			break;
		}
		ll = ll->next;
	}	

	hid_device *keyboard;
	if((keyboard = hid_open_path(ll->path)) == NULL){
		return 1;
	}

	unsigned char *data =   "\x00\x00\x1f\x00\x00\x00\x08\x0f\x03\x00\x00\x00\x00" \
				"\x00\x00\xff\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
				"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
				"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
				"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00" \
				"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xfb\x00";



	int sent = hid_send_feature_report(keyboard, data, sizeof(data) / sizeof(char));

	hid_exit();
}
