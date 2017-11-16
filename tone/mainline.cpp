#include <iostream>

#include <common.h>
#include <ice.h>
#include <rtcdc.h>
#include <dtls.h>
#include <util.h>
#include <dcep.h>
#include <sdp.h>

using std::cout;
using std::endl;

class PeerConnectionBase {
protected:
	rtcdc_peer_connection * peer;
public:
	PeerConnectionBase() : peer(0) { } 
	void Destroy() {
		cout << "Destroy called" << endl;
		if (peer!=0) {
			if (peer->user_data != 0) {
			}
			cout << "Calling rtcdc_destroy_peer_connection" << endl;
			rtcdc_destroy_peer_connection(peer);
		}
	}
	char * generate_offer() {
		cout << "PeerConnectionBase:generate_offer is called" << endl;
        	if (peer == 0) {
			cout << "generate_offer: peer is null!" << endl;
     		}
		if (peer!=0) {
			cout << "PeerConnectionBase:generate_offer:about to call generate offer sdp" << endl;
			return rtcdc_generate_offer_sdp(peer);
		} else {
			return 0;
		}
	}
};

void on_candidate_cb(struct rtcdc_peer_connection *peer,
                                      const char *candidate, void *user_data) {
	cout << "on_candidate_cb called: " << candidate << endl;
}
void on_channel_cb(struct rtcdc_peer_connection *peer,
                                    struct rtcdc_data_channel *channel, void *user_data) {
	cout << "on_channel_cb called" << endl;
}
void on_connect_cb(struct rtcdc_peer_connection *peer, void *user_data) {
	cout << "on_connect_cb called" << endl;
}

class PeerConnection : public PeerConnectionBase {
private:
	char * stun_server;
	int stun_port;
	//struct rtcdc_peer_connection * peer;
public:
	friend std::ostream& operator<<(std::ostream& os, PeerConnection& src);

	PeerConnection(char * stun_server, int stun_port) : 
		stun_server(stun_server), stun_port(stun_port)
		{
		if (stun_port==0) {
			// change to default port
		}
		cout << "PeerConnection ctor before rtcdc_create_peer_connection" << endl;
		peer = rtcdc_create_peer_connection(on_channel_cb,
			on_candidate_cb,
            on_connect_cb,
            stun_server, stun_port, 0);
		cout << "PeerConnection ctor after create_peer_connection" << endl;
	}
	~PeerConnection() {
		rtcdc_destroy_peer_connection(peer);
	}
};

std::ostream& operator<<(std::ostream& os, PeerConnection& src) {
	if (src.peer!=0) {
		os << "peer not 0";
	}
	return os;
}

int main(int argc, char** argv) {

	cout << "before PeerConnection" << endl;
	PeerConnection pc("stun.services.mozilla.com",443);
	cout << "after PeerConnection" << endl;
	char * offer = pc.generate_offer();
	if (offer==0) {
		cout << "got null offer" << endl;
	} else {
		cout << "offer: " << offer << endl;	
	}
	

	cout << "PC: " << pc << endl;
	


	return 0;
}
