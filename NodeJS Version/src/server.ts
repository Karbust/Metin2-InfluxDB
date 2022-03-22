import { CronJob } from 'cron'

import {
    gameHost,
    influxUrl,
    influxToken,
    influxOrg,
    influxBucket, gameSettings
} from './config';
import { getOnlinePlayers } from './functions'

import { InfluxDB, Point } from '@influxdata/influxdb-client'


const job = new CronJob('*/10 * * * *', () => {
    gameSettings.forEach((value) => {
        const playerCount = getOnlinePlayers(gameHost, value.port)

        const writeApi = new InfluxDB({ url: influxUrl, token: influxToken }).getWriteApi(influxOrg, influxBucket)
        const point = new Point(`online_users_${value.name}`)
            .intField('total', playerCount === -1 ? 0 : playerCount[0])
            .intField('empire1', playerCount === -1 ? 0 : playerCount[1])
            .intField('empire2', playerCount === -1 ? 0 : playerCount[2])
            .intField('empire3', playerCount === -1 ? 0 : playerCount[3])
        writeApi.writePoint(point)

        writeApi
            .close()
            .then(() => console.log(`Finished ${value.name} - ${value.port}`))
            .catch(e => {
                console.error(e)
                console.log(`Finished ERROR ${value.name} - ${value.port}`)
            })
    })
}, null, true, 'Europe/Lisbon');
job.start();
