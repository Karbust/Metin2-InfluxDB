import { SocketClientTCP } from 'netlinkwrapper'

import { gameAdminKey, gameHost, gameUserCount } from './config'

const getOnlinePlayers = (host: string, port: number): string[] | number => {
    const client = new SocketClientTCP(port, gameHost)

    let received: Buffer | String | undefined

    client.send(`\x40${gameAdminKey}\n`)
    client.receive()

    client.send(`\x40${gameUserCount}\n`)
    received = client.receive()

    if (received) {
        received = received.toString().replace(/\r?\n|\r/, '')

        if (!isNaN(Number(received.charAt(0)))) {
            const userCount = received.split(/[ ]+/)

            //console.log(`Total[${userCount[0]}] ${userCount[1]} / ${userCount[2]} / ${userCount[3]} (this server ${userCount[4]})`)

            client.disconnect()
            return userCount

        } else {
            //console.log(received)

            client.disconnect()
            return -1
        }
    } else {
        //console.log('An error occurred.')

        client.disconnect()
        return -1
    }
}

export {
    getOnlinePlayers
}
