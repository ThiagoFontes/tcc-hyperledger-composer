/*
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

'use strict';
/**
 * Write your transction processor functions here
 */

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
