import { CorsOptions } from 'cors'

const environment: string = process.env.NODE_ENV || 'development'

const gameHost: string = process.env.GAME_HOST
const gameAdminKey: string = process.env.GAME_ADMIN_KEY
const gameUserCount: string = process.env.GAME_USER_COUNT_COMMAND || 'USER_COUNT'

const gameSettings: Array<{name: string, port: number}> = [{
    name: 'channel1',
    port: 13001
}, {
    name: 'game99',
    port: 13099
}]

const influxUrl: string = process.env.INFLUX_URL
const influxToken: string = process.env.INFLUX_TOKEN
const influxOrg: string = process.env.INFLUX_ORG
const influxBucket: string = process.env.INFLUX_BUCKET

export {
    environment,
    serverPort,
    corsOptions,
    gameHost,
    gameAdminKey,
    gameUserCount,
    gameSettings,
    influxUrl,
    influxToken,
    influxOrg,
    influxBucket
}
