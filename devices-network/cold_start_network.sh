# Restart Fabric
../fabric-dev-servers/stopFabric.sh
time ../fabric-dev-servers/startFabric.sh

# Create peer admin card
../fabric-dev-servers/createPeerAdminCard.sh

# Instaling and starting devices-network
composer network install --card PeerAdmin@hlfv1 --archiveFile devices-network@0.0.1.bna
composer network start --networkName devices-network --networkVersion 0.0.1 --networkAdmin admin --networkAdminEnrollSecret adminpw --card PeerAdmin@hlfv1 --file networkadmin.card

# Deleting old card if exists and importing a new one
composer card delete --card admin@devices-network
composer card import --file networkadmin.card

# Testing configuration
composer network ping --card admin@devices-network

# Start REST server
composer-rest-server -c admin@devices-network -n never -u true -w true
