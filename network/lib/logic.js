/**
 * Track the device acess permission and ownership 
 * @param {dev.thiagofontes.givePermission} tx - the device to be processed
 * @transaction
 */
async function givePermission(tx) {
  tx.device.users.push(tx.addedUser);

  const assetRegistry = await getAssetRegistry('dev.thiagofontes.Device');
  await assetRegistry.update(tx.device);
}

async function revokePermission(tx) {
  for (var i = 0; i < tx.device.users.length; i++){
    if(tx.removedUser.userId === tx.device.users[i].userId) {
      tx.device.users.splice(i, 1); 
    }
  }

  const assetRegistry = await getAssetRegistry('dev.thiagofontes.Device');
  await assetRegistry.update(tx.device);
}