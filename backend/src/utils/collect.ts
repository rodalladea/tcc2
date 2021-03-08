import execa from 'execa';

const collect = async (site: string): Promise<void> => {
    await execa(`java -jar ./jars/collector.jar ${site}`);
};

export default collect;
