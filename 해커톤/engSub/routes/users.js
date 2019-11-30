var express = require('express');
var router = express.Router();

const secret = require('../config');
const jwt = require('../lib/token');

/* GET users listing. */
router.post('/login', async function(req, res, next) {
  let id = req.body.user_id;
  let pwd = req.body.user_pwd;
  
  if (id == 'skxotn' && pwd == '1234') {
    let token = null;
    var payload = {
      'user_id' : id
    }
    
    try {
      token = await jwt.generateToken(payload);
    } catch (error) {
      
    }
    
    res.cookie('access_token', token, {httpOnly: true, maxAge : 1000 * 60 * 60 * 24 * 7});
    res.send(true);
  } else {
    res.send(false);
  }
});

module.exports = router;
