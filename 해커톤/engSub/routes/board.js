var express = require('express');
var router = express.Router();
var fs = require('fs');
/*fs.readFile('lecture1.txt', 'utf8', function(err, data){
	console.log(data);
	});*/
const jwt = require('../lib/token');

router.get('/', async function(req, res, next) {
    let token = req.cookies.access_token;
    
    if(!token) res.render('index');
    let payload = await jwt.decodeToken(token);
    let user_id = payload.user_id;
    console.log(payload.user_id);
    res.render('board', {user_id : user_id});
})

router.get('/fileread', async function(req, res, next) {
	fs.readFile('routes/lecture1.txt', 'utf8', function(err, data){
	console.log(data);
	res.send(data);
	});
})

router.post('/filewrite', async function(req, res, next) {
	var temp = req.body.content;
	fs.writeFile('routes/lecture1.txt', temp ,'utf8', function(err){
		if(err) throw err;
	})
	res.location('/board');
})

module.exports = router;