import execa from 'execa';

const collect = async (): Promise<void> => {
    await execa('java -jar ./jars/merger.jar');
};

export default collect;
