../fabric-dev-servers/stopFabric.sh
../fabric-dev-servers/startFabric.sh
../fabric-dev-servers/createPeerAdminCard.sh

composer network install --card PeerAdmin@hlfv1 --archiveFile devices-network@0.0.1.bna
composer network start --networkName devices-network --networkVersion 0.0.1 --networkAdmin admin --networkAdminEnrollSecret adminpw --card PeerAdmin@hlfv1 --file networkadmin.card
composer card delete --card admin@devices-network
composer card import --file networkadmin.card
composer network ping --card admin@devices-network

