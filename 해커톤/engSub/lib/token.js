const config = require('../config');
const jwtSecret = config.secret;
const jwt = require('jsonwebtoken');

/**
 * JWT 토큰 생성
 * @param {any} payload 
 * @returns {string} token
 */
function generateToken(payload) {
    return new Promise(
        (resolve, reject) => {
            jwt.sign(
                payload,
                jwtSecret,
                {
                    expiresIn: '7d'
                }, (error, token) => {
                    if(error) reject(error);
                    resolve(token);
                }
            );
        }
    );
};

function decodeToken(token) {
    return new Promise(
        (resolve, reject) => {
            jwt.verify(token, jwtSecret, (err, decoded) => {
                if(err) {
                    reject(err);
                }
                resolve(decoded);
            })
        }
    )
}

exports.jwtMiddleware = async (ctx, next) => {
    const token = ctx.cookies.get('access_token');
    if(!token) {
        return next();
    }
    
    try {
        const decoded = await decodeToken(token);
        
        if(Date.now() / 1000 - decoded.iat > 60 * 60 * 24) {
            const {_id, profile} = decoded;
            const freshToken = await generateToken({_id, profile});
            ctx.cookies.set('access_token', freshToken, {httpOnly: true, maxAge : 1000 * 60 * 60 * 24 * 7});
        }
        
        ctx.request.user = decoded;
    } catch (e) {
        ctx.request.user = null;
    }
    
    return next();
}
exports.generateToken = generateToken;
exports.decodeToken = decodeToken;