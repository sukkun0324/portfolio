var express = require('express');
var router = express.Router();

let spawn = require('child_process').spawn;
let crypto = require('crypto');

const users = require('./users');
const board = require('./board');

/* GET home page. */
router.get('/', function(req, res, next) {
  res.render('index', { title: 'Express' });
});

let secret = "lotus_lantern#0614";

router.get('/push', function(req, res, next) {
    let deploySh = spawn('sh', ['test.sh']);
    deploySh.stdout.on('data', function (data) {
        let buff = new Buffer(data);
        console.log(buff.toString('utf-8'));
    });
    res.send('hi');
});
router.post('/push', function(req, res, next) {
    console.log('[LOG] request received');
    res.status(400).set('Content-Type', 'application/json');

    let jsonString = JSON.stringify(req.body);
    let hash = "sha1=" + crypto.createHmac('sha1', secret).update(jsonString).digest('hex');

    if (hash != req.get('x-hub-signature')) {
        console.log('[ERROR] invalid key');
        let data = JSON.stringify({ "error": "invalid key", key: hash });
        return res.end(data);
    }

    console.log("[LOG] running hook.sh");

    let deploySh = spawn('sh', ['hook.sh']);
    deploySh.stdout.on('data', function (data) {
        let buff = new Buffer(data);
        console.log(buff.toString('utf-8'));
    });

    let data = JSON.stringify({ "success": true });
    console.log('[LOG] success!!');
    return res.status(200).end(data);
});

router.use('/users', users);
router.use('/board', board);

module.exports = router;
