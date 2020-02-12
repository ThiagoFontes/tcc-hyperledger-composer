/**
 * Sample transaction processor function.
 * @param {dev.thiagofontes.givePermission} tx The sample transaction instance.
 * @transaction
 */
async function givePermission(tx) {
  tx.device.users.push(tx.addedUser);
  
  const assetRegistry = await getAssetRegistry('dev.thiagofontes.Device');
  await assetRegistry.update(tx.device);
}

/**
 * Sample transaction processor function.
 * @param {dev.thiagofontes.revokePermission} tx The sample transaction instance.
 * @transaction
 */
async function revokePermission(tx) {
  for (var i = 0; i < tx.device.users.length; i++){
    if(tx.removedUser.userId === tx.device.users[i].userId) {
      tx.device.users.splice(i, 1); 
    }
  }

  const assetRegistry = await getAssetRegistry('dev.thiagofontes.Device');
  await assetRegistry.update(tx.device);
}